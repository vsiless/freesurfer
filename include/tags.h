#ifndef TAGS_H
#define TAGS_H

#define TAG_OLD_COLORTABLE          1
#define TAG_OLD_USEREALRAS          2
#define TAG_CMDLINE                 3
#define TAG_USEREALRAS              4
#define TAG_COLORTABLE              5

#define TAG_GCAMORPH_GEOM           10
#define TAG_GCAMORPH_TYPE           11
#define TAG_GCAMORPH_LABELS         12

#define TAG_OLD_SURF_GEOM           20
#define TAG_SURF_GEOM               21

#define TAG_OLD_MGH_XFORM           30
#define TAG_MGH_XFORM               31
#define TAG_GROUP_AVG_SURFACE_AREA  32

int TAGreadStart(FILE *fp, long long *plen) ;
int TAGwriteStart(FILE *fp, int tag, long long *phere, long long len) ;
int TAGwriteEnd(FILE *fp, long long there) ;
int TAGskip(FILE *fp, int tag, long long len) ;
int TAGmakeCommandLineString(int argc, char **argv, char *cmd_line) ;
int TAGwriteCommandLine(FILE *fp, char *cmd_line) ;
int TAGwrite(FILE *fp, int tag, void *buf, long long len) ;
 
#endif
