
public class bank extends Thread{
	private int a;

	public bank(){
		this.a=100;
	}


	public void run(){
		while(true){
			a=a-1;
			try {
			//Thread.sleep(1000);
			

		} 
		catch (InterruptedException e) {
			System.out.println("ok!");
			break;
			
		}
			
			System.out.println(a);
		}



		
	}
}