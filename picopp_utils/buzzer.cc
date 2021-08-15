#include "buzzer.h"


namespace PicoPP::PWM {


Buzzer::Buzzer(Pin p, Slice& slice) :
	slice(slice.slice),
	pin(slice.slice, p)
{
	off();
}


}
