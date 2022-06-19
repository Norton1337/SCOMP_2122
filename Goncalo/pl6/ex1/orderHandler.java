
import java.util.NoSuchElementException;


public class orderHandler extends Thread{
	private Object myLock = new Object();

	
	public void handle(){
		

		while(true){//A CADA 3 SEGUNDOS IR VER SE EXISTE PEDIDOS
			try{
				Thread.sleep(3000);
			}
			catch(InterruptedException ex){
				System.out.println(ex);
			}
			synchronized(myLock){
				handleOrder();

			}


			
		}


	}

	public void handleOrder(){
		try{
			

			System.out.println(orderQueue.orders.getFirst().a);
			orderQueue.orders.removeFirst();

			}
			
		catch(NoSuchElementException ex){

		}
		return;

	}


}