#include "Mat4.h"
#include <stdio.h>

Mat4::Mat4() {
	mat = (float*)calloc(16, sizeof(float));
}

Mat4 *Mat4::initIdentity() {
	mat[0] = 1;
	mat[4] = 0;
	mat[8] = 0;
	mat[12] = 0;
	
	mat[1] = 0;
	mat[5] = 1;
	mat[9] = 0;
	mat[13] = 0;
	
	mat[2] = 0;
	mat[6] = 0;
	mat[10] = 1;
	mat[14] = 0;
	
	mat[3] = 0;
	mat[7] = 0;
	mat[11] = 0;
	mat[15] = 1;

	return this;
}

 Mat4 *Mat4::initTranslation(float x, float y, float z) {
	mat[0] = 1;
	mat[4] = 0;
	mat[8] = 0;
	mat[12] = x;

	mat[1] = 0;
	mat[5] = 1;
	mat[9] = 0;
	mat[13] = y;

	mat[2] = 0;
	mat[6] = 0;
	mat[10] = 1;
	mat[14] = z;

	mat[3] = 0;
	mat[7] = 0;
	mat[11] = 0;
	mat[15] = 1;

	return this;
}

 Mat4 *Mat4::initScale(float x, float y, float z) {
	 mat[0] = x;
	 mat[4] = 0;
	 mat[8] = 0;
	 mat[12] = 0;

	 mat[1] = 0;
	 mat[5] = y;
	 mat[9] = 0;
	 mat[13] = 0;

	 mat[2] = 0;
	 mat[6] = 0;
	 mat[10] = z;
	 mat[14] = 0;

	 mat[3] = 0;
	 mat[7] = 0;
	 mat[11] = 0;
	 mat[15] = 1;

	 return this;
 }

Mat4 *Mat4::initRotation(float x, float y, float z) {
	Mat4 rx = Mat4();
	rx.initIdentity();
	Mat4 ry = Mat4();
	ry.initIdentity();
	Mat4 rz = Mat4();
	rz.initIdentity();

	rz.mat[0] = cosf(z);
	rz.mat[4] = -sinf(z);
	rz.mat[1] = sinf(z);
	rz.mat[5] = cosf(z);

	rx.mat[5] = cosf(x);
	rx.mat[9] = -sinf(x);
	rx.mat[6] = sinf(x);
	rx.mat[10] = cosf(x);

	ry.mat[0] = cosf(y);
	ry.mat[8] = -sinf(y);
	ry.mat[2] = sinf(y);
	ry.mat[10] = cosf(y);

	Mat4 rxry = Mat4();
	Mat4 rxryrz = Mat4();
	rx.mul(&rxry, &ry);
	rxry.mul(&rxryrz, &rz);
    copy(&rxryrz);
	return this;
}




void Mat4::copy(Mat4 *src) {
	memcpy(this->mat, src->mat, MAT4_BYTESIZE);
}

Mat4 *Mat4::mul(Mat4 *dest, Mat4 *other) {
	dest->mat[0 + (0 * 4)] = mat[0 + (0 * 4)] * other->mat[0 + (0 * 4)] +
                       mat[0 + (1 * 4)] * other->mat[1 + (0 * 4)] +
                       mat[0 + (2 * 4)] * other->mat[2 + (0 * 4)] +
                       mat[0 + (3 * 4)] * other->mat[3 + (0 * 4)];
    dest->mat[0 + (1 * 4)] = mat[0 + (0 * 4)] * other->mat[0 + (1 * 4)] +
                       mat[0 + (1 * 4)] * other->mat[1 + (1 * 4)] +
                       mat[0 + (2 * 4)] * other->mat[2 + (1 * 4)] +
                       mat[0 + (3 * 4)] * other->mat[3 + (1 * 4)];
    dest->mat[0 + (2 * 4)] = mat[0 + (0 * 4)] * other->mat[0 + (2 * 4)] +
                       mat[0 + (1 * 4)] * other->mat[1 + (2 * 4)] +
                       mat[0 + (2 * 4)] * other->mat[2 + (2 * 4)] +
                       mat[0 + (3 * 4)] * other->mat[3 + (2 * 4)];
    dest->mat[0 + (3 * 4)] = mat[0 + (0 * 4)] * other->mat[0 + (3 * 4)] +
                       mat[0 + (1 * 4)] * other->mat[1 + (3 * 4)] +
                       mat[0 + (2 * 4)] * other->mat[2 + (3 * 4)] +
                       mat[0 + (3 * 4)] * other->mat[3 + (3 * 4)];
    dest->mat[1 + (0 * 4)] = mat[1 + (0 * 4)] * other->mat[0 + (0 * 4)] +
                       mat[1 + (1 * 4)] * other->mat[1 + (0 * 4)] +
                       mat[1 + (2 * 4)] * other->mat[2 + (0 * 4)] +
                       mat[1 + (3 * 4)] * other->mat[3 + (0 * 4)];
    dest->mat[1 + (1 * 4)] = mat[1 + (0 * 4)] * other->mat[0 + (1 * 4)] +
                       mat[1 + (1 * 4)] * other->mat[1 + (1 * 4)] +
                       mat[1 + (2 * 4)] * other->mat[2 + (1 * 4)] +
                       mat[1 + (3 * 4)] * other->mat[3 + (1 * 4)];
    dest->mat[1 + (2 * 4)] = mat[1 + (0 * 4)] * other->mat[0 + (2 * 4)] +
                       mat[1 + (1 * 4)] * other->mat[1 + (2 * 4)] +
                       mat[1 + (2 * 4)] * other->mat[2 + (2 * 4)] +
                       mat[1 + (3 * 4)] * other->mat[3 + (2 * 4)];
    dest->mat[1 + (3 * 4)] = mat[1 + (0 * 4)] * other->mat[0 + (3 * 4)] +
                       mat[1 + (1 * 4)] * other->mat[1 + (3 * 4)] +
                       mat[1 + (2 * 4)] * other->mat[2 + (3 * 4)] +
                       mat[1 + (3 * 4)] * other->mat[3 + (3 * 4)];
    dest->mat[2 + (0 * 4)] = mat[2 + (0 * 4)] * other->mat[0 + (0 * 4)] +
                       mat[2 + (1 * 4)] * other->mat[1 + (0 * 4)] +
                       mat[2 + (2 * 4)] * other->mat[2 + (0 * 4)] +
                       mat[2 + (3 * 4)] * other->mat[3 + (0 * 4)];
    dest->mat[2 + (1 * 4)] = mat[2 + (0 * 4)] * other->mat[0 + (1 * 4)] +
                       mat[2 + (1 * 4)] * other->mat[1 + (1 * 4)] +
                       mat[2 + (2 * 4)] * other->mat[2 + (1 * 4)] +
                       mat[2 + (3 * 4)] * other->mat[3 + (1 * 4)];
    dest->mat[2 + (2 * 4)] = mat[2 + (0 * 4)] * other->mat[0 + (2 * 4)] +
                       mat[2 + (1 * 4)] * other->mat[1 + (2 * 4)] +
                       mat[2 + (2 * 4)] * other->mat[2 + (2 * 4)] +
                       mat[2 + (3 * 4)] * other->mat[3 + (2 * 4)];
    dest->mat[2 + (3 * 4)] = mat[2 + (0 * 4)] * other->mat[0 + (3 * 4)] +
                       mat[2 + (1 * 4)] * other->mat[1 + (3 * 4)] +
                       mat[2 + (2 * 4)] * other->mat[2 + (3 * 4)] +
                       mat[2 + (3 * 4)] * other->mat[3 + (3 * 4)];
    dest->mat[3 + (0 * 4)] = mat[3 + (0 * 4)] * other->mat[0 + (0 * 4)] +
                       mat[3 + (1 * 4)] * other->mat[1 + (0 * 4)] +
                       mat[3 + (2 * 4)] * other->mat[2 + (0 * 4)] +
                       mat[3 + (3 * 4)] * other->mat[3 + (0 * 4)];
    dest->mat[3 + (1 * 4)] = mat[3 + (0 * 4)] * other->mat[0 + (1 * 4)] +
                       mat[3 + (1 * 4)] * other->mat[1 + (1 * 4)] +
                       mat[3 + (2 * 4)] * other->mat[2 + (1 * 4)] +
                       mat[3 + (3 * 4)] * other->mat[3 + (1 * 4)];
    dest->mat[3 + (2 * 4)] = mat[3 + (0 * 4)] * other->mat[0 + (2 * 4)] +
                       mat[3 + (1 * 4)] * other->mat[1 + (2 * 4)] +
                       mat[3 + (2 * 4)] * other->mat[2 + (2 * 4)] +
                       mat[3 + (3 * 4)] * other->mat[3 + (2 * 4)];
    dest->mat[3 + (3 * 4)] = mat[3 + (0 * 4)] * other->mat[0 + (3 * 4)] +
                       mat[3 + (1 * 4)] * other->mat[1 + (3 * 4)] +
                       mat[3 + (2 * 4)] * other->mat[2 + (3 * 4)] +
                       mat[3 + (3 * 4)] * other->mat[3 + (3 * 4)];
	return dest;
}

Mat4 *Mat4::perspective(float fov, float aspect, float zNear, float zFar) {
	float tanHalfFOV = tanf((fov * PI / 180) / 2);
	float zRange = zNear - zFar;
	mat[0] = 1 / (tanHalfFOV * aspect);
	mat[4] = 0;
	mat[8] = 0;
	mat[12] = 0;
	mat[1] = 0;
	mat[5] = 1 / tanHalfFOV;
	mat[9] = 0;
	mat[13] = 0;
	mat[2] = 0;
	mat[6] = 0;
	mat[10] = (-zNear - zFar) / zRange;
	mat[14] = 2 * zNear * zFar / zRange;
	mat[3] = 0;
	mat[7] = 0;
	mat[11] = 1;
	mat[15] = 0;
	return this;
}





Mat4::~Mat4() {
	delete(mat);
}
