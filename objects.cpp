Table::Table() {
	mBox.x = 680;
	mBox.y = 500;
	mBox.w = 55;
	mBox.h = 58;
}

Warp::Warp() {
	mBox.x = 630;
	mBox.y = 775;
	mBox.w = 10;
	mBox.h = 1;
}

Bed::Bed() {
	mBox.x = 480;
	mBox.y = 450;
	mBox.w = 40;
	mBox.h = 60;
}

SDL_Rect Warp::getBox() {
	return mBox;
}

void Warp::setWarp(int x, int y, int w, int h) {
	mBox.x = x; mBox.y = y;
	mBox.w = w; mBox.h = h;
}

SDL_Rect Table::getBox() {
	return mBox;
}

SDL_Rect Bed::getBox() {
	return mBox;
}

bool Warp::checkWarp (Chara* chara, int addRadius) {
	mBox.w += addRadius; mBox.h += addRadius;
	mBox.x -= addRadius; mBox.y -= addRadius;
	if(checkCollision(chara->getBox(), mBox)) {
		mBox.w -= addRadius; mBox.h -= addRadius;
		mBox.x += addRadius; mBox.y += addRadius;
		return 1;
	} else {
		mBox.w -= addRadius; mBox.h -= addRadius;
		mBox.x += addRadius; mBox.y += addRadius;
		return 0;
	}
}

bool bedMove = 0;
bool bedHasMoved = 0;
bool interruptBedMove = 0;
void Bed::moveToXY(int x, int y, Chara* chara) {
	if(!checkCollision(chara->getBox(), mBox)) {
	if(mBox.x != x && mBox.x < x) {
		mBox.x += 2;
		if(mBox.x > x)
			mBox.x -= 1;
	} else if(mBox.x != x && mBox.x > x) {
		mBox.x -= 2;
		if(mBox.x < x)
			mBox.x += 1;
	} else if(mBox.y != y && mBox.y < y) {
		mBox.y += 2;
		if(mBox.y > y)
			mBox.y -= 1;
	} else if(mBox.y != y && mBox.y > y) {
		mBox.y -= 2;
		if(mBox.y < y)
			mBox.y += 1;
	}
	} else {
		interruptBedMove = 1;
		if(mBox.x != x && mBox.x < x) {
		mBox.x -= 1;
	} else if(mBox.x != x && mBox.x > x) {
		mBox.x += 1;
	} else if(mBox.y != y && mBox.y < y) {
		mBox.y -= 1;
	} else if(mBox.y != y && mBox.y > y) {
		mBox.y += 1;
	}
	}

	if(mBox.x == x && mBox.y == y) {
		bedMove = 0;
		bedHasMoved = 1;
		interruptBedMove = 0;
	}
}

void Bed::setPos(int x, int y) {
	mBox.x = x; mBox.y = y;
}
