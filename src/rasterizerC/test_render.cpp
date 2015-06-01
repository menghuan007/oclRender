#include "oclrender.h"
#include <cstdlib>
#include <fstream>

using namespace std;
void test_picture()
{
	fstream f, fbg;
	f.open("test_picture.ppm", fstream::out | fstream::binary);
	fbg.open("../../pic/50608556_p0.ppm", fstream::in | fstream::binary);
	if (!fbg.is_open()) {
		exit(1);
	}
	PPMImage image(512, init_Color(0.0, 0.0, 0.0, 1.0));
	PPMImage bg(fbg);
	fbg.close();
	Scene scene;

	// add shapes
	Color lscolor;
	init_Color(&lscolor, 1.0, 0.0, 0.0, 1.0);
	scene.add(new ConvexPoly(LineSegment(Vector(0.0, 0), Vector(0.0, 1), 0.01, &lscolor)));
	scene.add(new ConvexPoly(LineSegment(Vector(0.1, 0), Vector(0.1, 1), 0.01, &lscolor)));
	scene.add(new ConvexPoly(LineSegment(Vector(0.2, 0), Vector(0.2, 1), 0.01, &lscolor)));
	scene.add(new ConvexPoly(LineSegment(Vector(0.3, 0), Vector(0.3, 1), 0.01, &lscolor)));
	scene.add(new ConvexPoly(LineSegment(Vector(0.4, 0), Vector(0.4, 1), 0.01, &lscolor).transform(around(Vector(0.5,0.5),rotate(1.57)))));

	//ConvexPoly some(LineSegment(Vector(0.4, 0), Vector(0.4, 1), 0.01, &lscolor));
	Color blue = init_Color(.0, .0, 1.0, 0.5);
	//ConvexPoly tri(Triangle({ Vector(0.5, 1), Vector(0, 0), Vector(1, 0) }, &blue));
	//scene.add(&tri);
	Color green = init_Color(.0, 1.0, .0, 1.0);
	Ellipse circle(Circle(Vector(0.75, 0.1), 0.5, &green));

	Transform rot(rotate(3.14159 * (1.0 / 2.0 + 1.0 / 8.0)));
	Transform sca(scale(1, 0.2));
	Ellipse ellip(circle.transform(around(Vector(0.75, 0.1), rot * sca)));
	scene.add(&ellip);
	scene.draw(bg);
	//image.write_ppm(f, &bg);
	bg.write_ppm(f);
	f.close();
}

int main()
{
	test_picture();
	return 0;
}