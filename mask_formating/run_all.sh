#!/bin/bash

root_dir="/home/hcrws1/acp/amazon_picking_challenge"

for dir in `ls $root_dir`; do
	echo "working on $dir..."
	mkdir $root_dir/$dir/cropped
	./image_processor $root_dir/$dir/masks
done