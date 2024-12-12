#include "Camera.h"

Camera::Camera() {};
// óñòàíîâêà ïîçèöèè êàìåðû
void Camera::setPosition(vec3 position)
{
	// îïðåäåëÿåì ðàäèóñ - ðàññòîÿíèå îò íà÷àëà ñèñòåìû êîîðäèíàò äî çàäàííîé ïîçèöèè
	r = length(position);
	// îïðåäåëÿåì âåðòèêàëüíûé óãîë:
	// ýòî óãîë ìåæäó âåêòîðîì èç íà÷àëà êîîðäèíàò ê íàáëþäàòåëþ (v1)
	// è ïðîåêöèåé ýòîãî âåêòîðà íà ãîðèçîíòàëüíóþ ïëîñêîñòü (v2)
	// äëÿ îïðåäåëåíèÿ óãëà èñïîëüçóåòñÿ ñêàëÿðíîå ïðîèçâåäåíèå íîðìàëèçîâàííûõ âåêòîðîâ
	vec3 v1 = position;
	vec3 v2 = vec3(v1.x, 0, v1.z);
	float cos_y = dot(normalize(v1), normalize(v2));
	angleY = degrees(acos(cos_y));
	// àíàëîãè÷íûì îáðàçîì îïðåäåëÿåì ãîðèçîíòàëüíûé óãîë:
	// ýòî óãîë ìåæäó ïðîåêöèåé (v2) è åäèíè÷íûì âåêòîðîì âäîëü îñè Ox
	float cos_x = dot(normalize(v2), vec3(1, 0, 0));
	angleX = degrees(acos(cos_x));
	// ïåðåñ÷èòûâàåì ïîçèöèþ (äëÿ êîððåêòèðîâîê îøèáîê îêðóãëåíèÿ)
	recalculatePosition();
}

vec3 Camera::getPosition() { return position; }
float Camera::getAngleX() { return angleX; }
float Camera::getAngleY() { return angleY; }
float Camera::getR() { return r; }
//ôóíêöèè äëÿ ïåðåìåùåíèÿ êàìåðû

void Camera::rotateLeftRight(float degree) {
	angleY = getAngleY() + degree;
	recalculatePosition();
}

void Camera::rotateUpDown(float degree) {
	float oldX = getAngleX();
	angleX = getAngleX() + degree;
	if ((angleX >= 5) && (angleX <= 85)) {
		recalculatePosition();
	}
	else {
		angleX = oldX;
		recalculatePosition();
	}
}

void Camera::zoomInOut(float distance) {
	float oldR = getR();
	r = getR() + distance;
	if ((r >= 15) && (r <= 55)) {
		recalculatePosition();
	}
	else {
		r = oldR;
		recalculatePosition();
	}
}



void Camera::apply() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(getPosition().x, getPosition().y, getPosition().z, 0, 0, 0, 0, 1, 0);
}

void Camera::recalculatePosition() {
	vec3 eye;
	eye.x = r * cos(radians(angleY)) * cos(radians(angleX));
	eye.y = r * sin(radians(angleX));
	eye.z = r * sin(radians(angleY)) * cos(radians(angleX));
	position = eye;
	apply();
}