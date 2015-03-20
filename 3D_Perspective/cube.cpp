#include "cube.h"

Cube::Cube(){
	Point3D tmpr_point;
	Line3D tmpr_line(tmpr_point,tmpr_point);	
	//for (int i=0; i<12;i++) edges.push_back(tmpr_line);	
	edges.assign(12,tmpr_line);
}
	
Cube::Cube(vector<Line3D> sisi){
	for (vector<Line3D>::iterator it=sisi.begin(); it!=sisi.end();++it){
		edges.push_back(*it);		
	}
}

Cube::Cube(const Cube& kubus){
	vector<Line3D> sisi;
	sisi=kubus.getAllSide();
	for (vector<Line3D>::iterator it=sisi.begin(); it!=sisi.end();++it){
		this->edges.push_back(*it);		
	}
}

Cube& Cube::operator= (const Cube& kubus){
	if (!(this->edges.empty())){
		vector<Line3D> sisi;
		sisi=kubus.getAllSide();
		for (int i=0; i<this->edges.size();i++){
			this->edges[i]=sisi[i];
		}
	}
	return *this;
}

Cube::~Cube(){	
	edges.clear();
}

vector<Point3D> Cube::getSide(int i){
	return edges[i].getPoints();
}

void Cube::setSide(int i,Line3D satu_sisi){
	this->edges[i]=satu_sisi;
}

vector<Line3D> Cube::getAllSide() const{
	return edges;
}	
