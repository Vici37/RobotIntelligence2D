This is the 2D object recognition part for the Amazon Picking Challenge using
Caffe.

Directories and Contents
========================

training
--------
This directory contains files relavent to training of the neural network.

classifying
-----------
Files relavent to taking a pretrained neural network and image and giving its
classification.

mask_formatting
---------------
All Amazon Picking Challenge images come with a mask of where the object is.
This directory contains code that will use those masks and create smaller images
of just the objects for training.

image_warp
----------
All images contain white background, allowing the neural network to learn that
should the background change, it's most likely due to the object being
different. This is not true of real data, so this dirctory contains code that
will take an image and perform various warpings on it (adding noise, changing
the background, etc.) and creates more training data.
