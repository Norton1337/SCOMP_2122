

public class orderT extends Thread{

	orderHandler oH;
	public orderT(orderHandler oH){
		this.oH=oH;

	}


	public void run(){
		
		oH.handle();






	}




}