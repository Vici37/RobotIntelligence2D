#!/bin/bash


# CHANGE THESE
CAFFE_TOOLS=/home/tsornson/programming/caffe/caffe/build/tools
TRAIN_IMAGES_ROOT=/home/tsornson/school/robot_intelligence/amazon_picking_challenge/scaled_images/
TRAIN_IMAGES_LIST=${TRAIN_IMAGES_ROOT}file_list.txt
TEST_IMAGES_ROOT=/home/tsornson/school/robot_intelligence/amazon_picking_challenge/scaled_images/
TEST_IMAGES_LIST=${TEST_IMAGES_ROOT}file_list.txt
SOLVER=/home/tsornson/school/robot_intelligence/amazon_picking_challenge/training/solver.prototxt

# DONT CHANGE THESE
TRAIN_IMAGES_DB=${TRAIN_IMAGES_ROOT}dbs/train.lmdb
TRAIN_IMAGES_MEAN=${TRAIN_IMAGES_ROOT}dbs/train.lmdb/train_mean.binaryproto
TEST_IMAGES_DB=${TEST_IMAGES_ROOT}dbs/test.lmdb


REBUILD=0

if [[ REBUILD -eq 1 ]]; then
  # Convert images into lmdb format
  # Training
  echo "Converting training images into lmdb"
  echo
  rm -rf ${TRAIN_IMAGES_DB}
  ${CAFFE_TOOLS}/convert_imageset --shuffle ${TRAIN_IMAGES_ROOT} ${TRAIN_IMAGES_LIST} ${TRAIN_IMAGES_DB}
  echo
  echo "Done"
  echo
  echo "Converting testing images into lmdb"
  echo
  rm -rf ${TEST_IMAGES_DB}
  ${CAFFE_TOOLS}/convert_imageset --shuffle ${TEST_IMAGES_ROOT} ${TEST_IMAGES_LIST} ${TEST_IMAGES_DB}
  echo
  echo "Done"
  echo

  # Compute the image mean
  echo "Creating train mean file"
  echo
  ${CAFFE_TOOLS}/compute_image_mean ${TRAIN_IMAGES_DB} ${TRAIN_IMAGES_MEAN}
  echo "Done"
  echo
fi

echo "Training"
echo
${CAFFE_TOOLS}/caffe train --solver=${SOLVER}
