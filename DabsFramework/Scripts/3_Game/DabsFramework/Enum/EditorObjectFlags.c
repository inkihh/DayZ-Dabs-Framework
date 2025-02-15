const int EFE_DEFAULT = EditorObjectFlags.BBOX | EditorObjectFlags.MAPMARKER | EditorObjectFlags.OBJECTMARKER | EditorObjectFlags.LISTITEM;

enum EditorObjectFlags
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