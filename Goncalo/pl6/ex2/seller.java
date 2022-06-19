

public class seller extends Thread{

	private tickets tic;
	private int a;
	public seller(tickets tic,int a){
		this.tic=tic;
		this.a=a;
	}



	public void run(){


		while(true){
			


			tic.sell(a);

		}



	}




}