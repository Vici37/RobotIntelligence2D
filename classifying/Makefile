CAFFE_ROOT=/home/tsornson/programming/caffe/caffe
FLAGS=-O2 -DCPU_ONLY
LINKS=-lglog -lcaffe -lprotobuf
EXE=classify
MAIN=caffe_test.cpp

all:
	g++ -o ${EXE} ${MAIN} \
		-I${CAFFE_ROOT}/include/ \
		-I${CAFFE_ROOT}/src/caf \
		-L${CAFFE_ROOT}/build/lib \
		${FLAGS} \
		${LINKS}

clean: c
c:
	rm -f ${EXE}
