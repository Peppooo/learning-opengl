#pragma once
struct Vec3 {
	float x,y,z;
	Vec3():x(0),y(0),z(0) {}
	Vec3(float X,float Y,float Z):x(X),y(Y),z(Z) {}
};

struct Vec2 {
	float x,y;
	Vec2(): x(0),y(0) {}
	Vec2(float X,float Y): x(X),y(Y) {}
};

struct Vert {
	Vec3 pos,norm;
	Vec2 tex;
	Vert():pos(Vec3()),norm(Vec3()),tex(Vec2()) {}
	Vert(Vec3 Pos,Vec3 Norm,Vec2 Tex):pos(Pos),norm(Norm),tex(Tex) {}
};