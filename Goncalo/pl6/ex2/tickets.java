public class tickets{

	public int ticket;

	private Object obj=new Object();

	public tickets(){
		ticket=2000;
	}



	public void sell(int thread){
		synchronized(obj){
			System.out.println(ticket+" vendido pela thread ->"+thread);
			

			ticket--;

			if (ticket==0){
				System.exit(1);
			}

		}
	}





}