#ifndef REIMU_STATIC_PLAYSTATUS_H
#define  REIMU_STATIC_PLAYSTATUS_H

/**< 击打统计结构体*/
 typedef struct  _PlayStatus
{
    unsigned short nowHit = 0; /**当前Hit数*/
    unsigned short maxHit = 0;/**最大Hit数*/
    unsigned int Mark = 0;/**总分*/
    unsigned short perferHit = 0;/**击打perfer总数*/
    unsigned short goodHit = 0;/**击打good总数*/
    unsigned short missHit = 0;/**miss总数*/
 }PlayStatus;


class PlayStatusStatic
{
public:
      static  PlayStatus  *playStatus;
      PlayStatusStatic();
};
#endif
