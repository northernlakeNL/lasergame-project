#include <rtos-master\rtos.hpp>

class schieten : public rtos::task<>{
	enum state_t{IDLE, SHOOT, RELOAD, EMPTYMAG};
	private:
		state_t	state = IDLE;
	
	rtos::flag			trPressFlag;
	rtos::flag			bnPressFlag;
	
	IREmittercontroller iREmittercontroller;
	Button				ReloadButton;
	Button				Trigger;
	DisplayController	DisplayController;
	SpeakerController	speakerController;
		
	Schieten(
		iREmittercontroller iREmittercontroller,
		Button& ReloadButton,
		Button& Trigger,
		DisplayController DisplayController,
		SpeakerController SpeakerController
		):{	
			ReloadButton.addButtonListener)(this);
			Trigger.addButtonListener(this);
		}

	
	public:
	void main(){
		for(;;){
			switch(state){
				case IDLE:
					auto evt = wait(bnPressFlag, trPressFlag);
					display.ShowInfo(defaultImage);
					if(evt == bnPressFlag){
						if(bullet > 1){
							bullet--;
							state = SHOOT;
							}
						else{
							state = EMPTYMAG;
						}
					}
					if(evt == trPressFlag){
						bullet = 30;
						state = RELOAD;
					}
				
				case RELOAD:
					speaker.Playsound(mp3);
					displayController.showInfo(update)bullet);
					// 500 ms exit
					timer.Start( 500'000'000 );
					state = IDLE;
				
				case EMPTYMAG:
					displayController.showInfo(defaultImage);
					speaker.playSound(clickingSound);
					// 300 ms exit
					timer.Start(300'000'000);
					state = IDLE
					
				case SHOOT:
					speaker.playSound(mp3);
					displayController.showInfo(update_bullet);
					IrEmitter.sendPulse(number); 
					// 200 ms exit
					timer.start(200'000'000)
					state = IDLE;
			}
		}
	}
}
