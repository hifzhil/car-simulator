import glob
import os
import sys

try:
    sys.path.append(glob.glob('../carla/dist/carla-*%d.%d-%s.egg' % (
        sys.version_info.major,
        sys.version_info.minor,
        'win-amd64' if os.name == 'nt' else 'linux-x86_64'))[0])
except IndexError:
    pass

import carla
import time
import numpy as np
import math

L = 2.875
Kdd = 4.0
alpha_prev = 0
delta_prev = 0

client = carla.Client('localhost', 2000)
client.set_timeout(200)

world = client.load_world("Town01")

world.set_weather(carla.WeatherParameters.ClearNoon)

bp_lib = world.get_blueprint_library()
vehicle_bp = bp_lib.filter('vehicle.tesla.model3')[0]

transform = carla.Transform()

transform.location.x = 220
transform.location.y = -1.6
transform.location.z = 1.85

transform.rotation.yaw = 180
transform.rotation.pitch = 0
transform.rotation.roll = 0

vehicle = world.spawn_actor(vehicle_bp, transform)

spectator = world.get_spectator()
sp_transform = carla.Transform(transform.location + carla.Location(z=90, x=-65, y=20),
                               carla.Rotation(yaw=90, pitch=-90))
spectator.set_transform(sp_transform)

control = carla.VehicleControl()
control.throttle = 0.5
vehicle.apply_control(control)

map = world.get_map()
waypoints = map.generate_waypoints(2.0)

# Vehicle Current Location
vehicle_loc = vehicle.get_location()
wp = map.get_waypoint(vehicle_loc, project_to_road=True,
                      lane_type=carla.LaneType.Driving)

waypoint_list = []
waypoint_obj_list = []

# print values
def display(disp=False):
    if disp:
        print("--"*20)
        print("\nMin Index= ", min_index)
        print("Forward Vel= %.3f m/s"%vf)
        print("Lookahead Dist= %.2f m"%ld)
        print("Alpha= %.5f rad"%alpha)
        print("Delta= %.5f rad"%steer_angle)
        print("Error= %.3f m"%e)

# Calculate Delta
def calc_steering_angle(alpha, ld):
    delta_prev = 0
    delta = math.atan2(2*L*np.sin(alpha), ld)
    delta = np.fmax(np.fmin(delta, 1.0), -1.0)
    if math.isnan(delta):
        delta = delta_prev
    else:
        delta_prev = delta
    
    return delta

# Get target waypoint index
def get_target_wp_index(veh_location, waypoint_list):
    dxl, dyl = [], []
    for i in range(len(waypoint_list)):
        dx = abs(veh_location.x - waypoint_list[i][0])
        dxl.append(dx)
        dy = abs(veh_location.y - waypoint_list[i][1])
        dyl.append(dy)

    dist = np.hypot(dxl, dyl)
    idx = np.argmin(dist) + 4

    # take closest waypoint, else last wp
    if idx < len(waypoint_list):
        tx = waypoint_list[idx][0]
        ty = waypoint_list[idx][1]
    else:
        tx = waypoint_list[-1][0]
        ty = waypoint_list[-1][1]

    return idx, tx, ty, dist


def get_lookahead_dist(vf, idx, waypoint_list, dist):
    ld = Kdd*vf
    # while ld > dist[idx] and (idx+1) < len(waypoint_list):
    #     idx += 1
    return ld


# Debug Helper
def draw(loc1, loc2=None, type=None):
    if type == "string":
        world.debug.draw_string(loc1, "X",
                            life_time=2000, persistent_lines=True)
    elif type == "line":
        world.debug.draw_line(loc1, loc2, thickness=0.8,
         color=carla.Color(r=0, g=255, b=0),
                        life_time=0.5, persistent_lines=True)
    elif type == "string2":
        world.debug.draw_string(loc1, "X", color=carla.Color(r=0, g=255, b=0),
                            life_time=0.3, persistent_lines=True)

# Generate waypoints
noOfWp = 100
t = 0
while t < noOfWp:
    wp_next = wp.next(2.0)
    if len(wp_next) > 1:
        wp = wp_next[1]
    else:
        wp = wp_next[0]

    waypoint_obj_list.append(wp)
    waypoint_list.insert(t, (wp.transform.location.x, wp.transform.location.y))
    draw(wp.transform.location, type="string")
    t += 1

# Game Loop
t = 0
while t < noOfWp:
    veh_transform = vehicle.get_transform()
    veh_location = vehicle.get_location()
    veh_vel = vehicle.get_velocity()
    vf = np.sqrt(veh_vel.x**2 + veh_vel.y**2)
    vf = np.fmax(np.fmin(vf, 2.5), 0.1)

    min_index, tx, ty, dist = get_target_wp_index(veh_location, waypoint_list)
    ld = get_lookahead_dist(vf, min_index, waypoint_list, dist)


    yaw = np.radians(veh_transform.rotation.yaw)
    alpha = math.atan2(ty-veh_location.y, tx-veh_location.x) - yaw
    # alpha = np.arccos((ex*np.cos(yaw)+ey*np.sin(yaw))/ld)

    if math.isnan(alpha):
        alpha = alpha_prev
    else:
        alpha_prev = alpha

    e = np.sin(alpha)*ld
    
    steer_angle = calc_steering_angle(alpha, ld)
    control.steer = steer_angle
    vehicle.apply_control(control)

    # draw(veh_location, waypoint_obj_list[min_index].transform.location, type="line")
    draw(waypoint_obj_list[min_index].transform.location, type="string2")
    display(disp=True)

    time.sleep(0.5)
    t += 1

print("Task Done!")
vehicle.destroy()