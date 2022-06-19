import java.util.LinkedList;
//import orderTaker;

public class orderQueue{

	public static LinkedList<order> orders = new LinkedList<order>();




//É GERADOS VARIAS THREADS ORDERTAKER(10) E APENAS 2 ORDERHANDLER PARA PEGAR NOS PEDIDOS
	public static void main(String[] arg){
		int d;
		orderHandler ordH=new orderHandler();
		orderT oT;
		for(d=0;d<2;d=d+1){
			oT=new orderT(ordH);
			oT.start();
		}

		orderTaker ordT;
		for(d=0;d<10;d=d+1){
			ordT=new orderTaker();
			ordT.start();
		}

		try{
			Thread.sleep(3000);
		}
		catch(InterruptedException ex){
			System.out.println(ex);
		}

		






		try{
			Thread.sleep(20000);//programa dura 15s
		}
		catch(InterruptedException ex){
			System.out.println(ex);
		}
		System.exit(1);
		




	}









}