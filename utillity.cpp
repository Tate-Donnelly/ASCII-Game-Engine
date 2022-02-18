#include "utillity.h"
#include "LogManager.h"
#include "WorldManager.h"

#include <cmath>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdarg.h>
namespace df {

	//Gives the current time as a string
	char* utillity::getTimeString() {
		static char time_str[30];
		time_t now;
		time(&now);
		struct tm p_time;
		localtime_s(&p_time, &now);

		sprintf_s(time_str, "%02d: %02d : %02d", p_time.tm_hour, p_time.tm_min, p_time.tm_sec);
		return time_str;
	}

	//Return true if two positions intersect, else false
	bool utillity::positionsIntersect(Vector p1, Vector p2) {
		LM.writeLog(0, "(%f, %f) and (%f, %f)", p1.getX(), p1.getY(), p2.getX(), p2.getY());
		if (((abs((int)(p1.getX() - p2.getX()))) <= 1) && ((abs((int)(p1.getY() - p2.getY()))) <= 1)) {
			return true;
		}
		return false;
	}

	// Convert relative bounding Box for Object to absolute world Box.
	Box utillity::getWorldBox(const Object* p_o) {
		return getWorldBox(p_o, p_o->getPosition());
	}

	// Convert relative bounding Box for Object to absolute world Box.
	Box utillity::getWorldBox(const Object* p_o, Vector where) {
		Box temp_box = p_o->getBox();
		Vector corner = temp_box.getCorner();
		Vector result(0,0);
		corner.setX(corner.getX() + where.getX());
		corner.setY(corner.getY() + where.getY());
		temp_box.setCorner(corner);

		return temp_box;
	}

	// Return true if boxes intersect, else false.
	bool utillity::boxIntersectsBox(Box A, Box B) {
		float Ax1 = A.getCorner().getX();
		float Ay1 = A.getCorner().getY();

		float Ax2 = Ax1 + A.getHorizontal();
		float Ay2 = Ay1 + A.getVertical();

		float Bx1 = B.getCorner().getX();
		float By1 = B.getCorner().getY();

		float Bx2 = Bx1 + B.getHorizontal();
		float By2 = By1 + B.getVertical();


		LM.writeLog(0,"A1 (%f, %f) ", Ax1, Ay1);
		LM.writeLog(0, "A2 (%f, %f) ", Ax2, Ay2);
		LM.writeLog(0, "B1 (%f, %f) ", Bx1, By1);
		LM.writeLog(0, "B2 (%f, %f) ", Bx2, By2);
		//Horizontal overlap
		bool x_overlap = ((Bx1 <= Ax1) && (Ax1 <= Bx2)) || ((Ax1 <= Bx1) && (Bx1 <= Ax2));
		//Vertical overlap
		bool y_overlap = ((By1 <= Ay1) && (Ay1 <= By2)) || ((Ay1 <= By1) && (By1 <= Ay2));

		if (x_overlap && y_overlap) {
			//LM.writeLog("OVERLAP");
			return true;
		}
		return false;
	}

	// Convert world position to view position.
	Vector utillity::worldToView(Vector world_pos){
		Vector view_origin = WM.getView().getCorner();
		float view_x = view_origin.getX();
		float view_y = view_origin.getY();
		Vector view_pos(world_pos.getX() - view_x, world_pos.getY() - view_y);
		return view_pos;
	}

	// Convert view position to world position.
	Vector utillity::viewToWorld(Vector view_pos) {
		Vector view_origin = WM.getView().getCorner();
		float view_x = view_origin.getX();
		float view_y = view_origin.getY();
		Vector world_pos(view_pos.getX() + view_x, view_pos.getY() + view_y);
		return world_pos;
	}

	// Convert int to a string, returning string.
	std::string utillity::toString(int i) {
		std::stringstream ss;  // Create stringstream.
		ss << i;          // Add number to stream.
		return ss.str();  // Return string with contents of stream.
	}
}