#ifndef  STRUCT_DOOM_INC
#define  STRUCT_DOOM_INC

/*
   This data structure contains the information about the THINGS
*/
typedef struct {
    int xpos;		/* x position */
    int ypos;		/* y position */
    int angle;		/* facing angle */
    int type;		/* thing type */
    int flags;		/* appears when? */
} Thing;

/*
   This data structure contains the information about the LINEDEFS
*/
typedef struct {
    int start;		/* from this vertex ... */
    int end;		/* ... to this vertex */
    int flags;		/* see NAMES.C for more info */
    int tag;
    int special;	/* see NAMES.C for more info */
    int sidedef1;	/* sidedef */
    int sidedef2;	/* only if this line adjoins 2 sectors */
} LineDef;

/*
   This data structure contains the information about the SIDEDEFS
*/
typedef struct {
    int xoff;			/* X offset for texture */
    int yoff;			/* Y offset for texture */
    char tex_upper[8];	/* texture name for the part above */
    char tex_lower[8];	/* texture name for the part below */
    char tex_normal[8];	/* texture name for the regular part */
    int sector;			/* adjacent sector  */
} SideDef;

/*
   This data structure contains the information about the VERTEXES
*/
typedef struct {
    int x;				/* X coordinate */
    int y;				/* Y coordinate */
} Vertex;

/*
   This data structure contains the information about the SEGS
*/
typedef struct {
    struct Seg *next;	/* next Seg in list */
    int start;			/* from this vertex ... */
    int end;			/* ... to this vertex */
    unsigned int angle;	/* angle (0 = east, 16384 = north, ...) */
    int linedef;		/* linedef that this seg goes along*/
    int flip;			/* true if not the same direction as linedef */
    unsigned int dist;	/* distance from starting point */
} Seg;

/*
	This data structure contains the information about the SSECTORS
*/
typedef struct {
    struct SSector *next;	/* next Sub-Sector in list */
    int num;				/* number of Segs in this Sub-Sector */
    int first;				/* first Seg */
} SSector;

/*
   This data structure contains the information about the NODES
*/
typedef struct {
    int x, y;							/* starting point */
    int dx, dy;							/* offset to ending point */
    int miny1, maxy1, minx1, maxx1;		/* bounding rectangle 1 */
    int miny2, maxy2, minx2, maxx2;		/* bounding rectangle 2 */
    int child1, child2;					/* Node or SSector (if high bit is set) */
    struct Node *node1, *node2;			/* pointer if the child is a Node */
    int num;							/* number given to this Node */
} Node;

/*
   This data structure contains the information about the SECTORS
*/
typedef struct {
    int height_floor;	/* floor height */
    int height_ceil;	/* ceiling height */
    char tex_floor[8];	/* floor texture */
    char tex_ceil[8];	/* ceiling texture */
    int light;			/* light level (0-255) */
    int special;		/* special behaviour (0 = normal, 9 = secret, ...) */
    int tag;			/* sector activated by a linedef with the same tag */
} Sector;

/*
   Structure for unknown behaviour
*/
typedef struct {
    int unknown1;
    int unknown2;
} Behavior;

/* SO: added these 2 25/02/95 to speed up displaying wall textures */
typedef struct {
    char name[8];		/* name of this texture */
    int zero1, zero2;	/* fields which are always zero */
    int width, height;	/* dimensions of this texture */
    int zero3, zero4;	/* fields which are always zero */
    int nPatches; 		/* number of patch descriptors following */
} Texture;

typedef struct {
    int xOffset, yOffset;
    int PatchNumber, One, Zero;
} PatchDesc;

/* these are to make drawing pictures easier */
typedef struct {
    int width, height;
    int xofs, yofs;
} PHeader;

typedef struct {
    unsigned char yofs, npixels;
} PColumn;

#endif
/* vim: set sw=4 ts=4 sts=4 ft=cpp expandtab: */

