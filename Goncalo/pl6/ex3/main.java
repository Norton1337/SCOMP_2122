
public class main{

	public static void main(String[] arg){
		bank obj=new bank();

		obj.start();

		try {
			Thread.sleep(10000);
			obj.interrupt();
			obj.join();

		} 
		catch (InterruptedException e) {
			System.out.println("erro!");
			
		}
		
		return;


	}
}