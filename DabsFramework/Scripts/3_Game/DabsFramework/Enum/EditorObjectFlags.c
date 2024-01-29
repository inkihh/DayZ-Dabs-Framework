const int EFE_DEFAULT = ObjectNodeFlags.BBOX | ObjectNodeFlags.MAPMARKER | ObjectNodeFlags.OBJECTMARKER | ObjectNodeFlags.LISTITEM;

enum ObjectNodeFlags
{
	NONE = 0,
	BBOX = 2,
	MAPMARKER = 4,
	OBJECTMARKER = 8,
	LISTITEM = 16,
	PERSISTENCE = 32,
	LOCKED = 64, 
	EDITOR_ONLY = 128, 
	SIMULATE = 256, 
	ALLOW_DAMAGE = 512,
	HIDDEN = 1024,
	ALL = 2147483647
};