rm ./xcb_threaded_unit_test_get_overlay_image_xy
cc -std=c11 -Wall -g -static  -L/usr/local/lib/ -lxcb -I/usr/local/include/ /root/dahlia_suite/xcb/unit_test/xcb_threaded_unit_test_get_overlay_image_xy.c -o xcb_threaded_unit_test_get_overlay_image_xy
