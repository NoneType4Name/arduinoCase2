// NoneType4Name.
#include <Servo.h>
#define LIGHTNESS       A0
#define MIN_ANGLE_SERVO 10
#define MAX_ANGLE_SERVO 150
#define MIN_LEN_SERVO   150
#define MAX_LEN_SERVO   160

Servo rotate;
Servo len;
Servo angle;

bool lightFinded { 0 };
uint32_t sleeped { 0 };

uint32_t minimumLinght { -1 };
uint32_t minAngle { -1 };
uint32_t minHeight { -1 };

struct
{
    uint32_t minimum { -1 };
    uint32_t rotate { -1 };
    uint32_t angle { -1 };
    uint32_t len { -1 };
} light;

void reset()
{
    minimumLinght = -1;
    minAngle      = -1;
    minHeight     = -1;
    rotate.write( 0 );
    len.write( MAX_LEN_SERVO );
    angle.write( MIN_ANGLE_SERVO );
}

void setup()
{
    Serial.begin( 9600 );
    rotate.attach( 9 );
    len.attach( 10 );
    angle.attach( 11 );
    pinMode( LIGHTNESS, INPUT );
    angle.write( MIN_ANGLE_SERVO );
    delay( 500 );
    angle.write( MAX_ANGLE_SERVO );
    delay( 500 );
}

void scan()
{
    for ( uint32_t rotateDegrees { 0 }; rotateDegrees <= 180; rotateDegrees += 10 )
    {
        rotate.write( rotateDegrees );
        angle.write( MIN_ANGLE_SERVO );
        len.write( MIN_LEN_SERVO );
        for ( uint32_t angleDegrees { MIN_ANGLE_SERVO }; angleDegrees <= MAX_ANGLE_SERVO; angleDegrees += 10 )
        {
            angle.write( angleDegrees );
            uint32_t lightness { analogRead( LIGHTNESS ) };
            if ( lightness < light.minimum )
            {
                light.minimum = lightness;
                light.angle   = angleDegrees;
                light.rotate  = angleDegrees;
                light.len     = MIN_LEN_SERVO;
            }
            delay( 100 );
        }
        delay( 100 );
        len.write( MAX_LEN_SERVO );
        delay( 100 );
        for ( uint32_t angleDegrees { MAX_ANGLE_SERVO }; angleDegrees >= MIN_ANGLE_SERVO; angleDegrees -= 10 )
        {
            angle.write( angleDegrees );
            uint32_t lightness { analogRead( LIGHTNESS ) };
            if ( lightness < light.minimum )
            {
                light.minimum = lightness;
                light.angle   = angleDegrees;
                light.rotate  = angleDegrees;
                light.len     = MAX_LEN_SERVO;
            }
            delay( 100 );
        }
        delay( 100 );
    }
}

void loop()
{
    reset();
    scan();
    rotate.write( light.rotate );
    angle.write( light.angle );
    len.write( light.len );
    delay( 10 * 1000 );
}