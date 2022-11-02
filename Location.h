#pragma once

struct Location {
	int x;
	int y;
	bool operator==(const Location& otherLocation) const
	{
		return x == otherLocation.x && y == otherLocation.y;
	}
};

