#!/bin/sh

module="driver_open"

/sbin/rmmod $module || exit 1
 

rm -f /dev/$module*


