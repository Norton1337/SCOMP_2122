


public class orderTaker extends Thread{

	private static int a=0;
	private int b;

	public void run(){
		b=a;
		this.a=a+1;
		System.out.println("Pedido feito-> "+b);
		orderQueue.orders.addLast(new order(b));

	}



}