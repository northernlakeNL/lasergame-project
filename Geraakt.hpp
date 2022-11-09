#include "hwlib.hpp"
#include "rtos.hpp"

class gunControlHit : public rtos::task<>{
    enum state_t {IDLE, RECEIVE, INVULNERABLE, VULNERABLE};
    
private:
    state_t state = IDLE;
    
    rtos::timer time;

    rtos::pool< uint8_t > ConvertBytePool;
    InternalStorage Storage;
    HitController HitControl;
    IR_ReceiverController IR_ReceiverControl;
    Invulnerable& Invulnerable;
    DisableGun& DisableGun;
    
    void main(){    

        for(;;){
            switch(state){
                case IDLE:
                auto evt = wait(IR_ReceiverControl, ConvertBytePool, time, HitControl, Storage, Invulnerable, DisableGun);
                if(evt == IR_ReceiverControl){
                    if(Invulnerable == false){
                        if(Storage.life > 0){
                            state = INVULNERABLE;
                        }
                    } else {
                        state = IDLE;
                    }
                }
                case INVULNERABLE:
                    ConvertBytePool.read();
                    Internal_storage.sendID();
                    DisableGun(true);
                    Invulerable.set(true);
                    if(Storage.life > 0){
                        state = VULNERABLE;
                    } else{
                        break; // end
                    }
                case VULNERABLE:
                    time.start(10'000'000);
                    DisableGun(false);
                    state = IDLE;
            }
        }
    }


    
public:
    gunControlHit();
    
    void ConvertByte( byte )
    {ConvertBytePool.read();}
    
};

int main( void ){    
   
   // wait for the PC console to start
   hwlib::wait_ms( 500 );
   
   hwlib::cout << "demo\n";
   
   namespace target = hwlib::target;
   
   auto Geraakt = gunControlHit();
   
   rtos::run();
}
