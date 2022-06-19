import java.util.List;
import java.util.ArrayList; 

public class barraca{


	public static void main(String[] arg){

		int d;
		
		tickets tic=new tickets();
		ArrayList<seller> sel=new ArrayList<seller>();

		for (d=0;d<5;d=d+1){
			sel.add(new seller(tic,d));
			

		}

		for (d=0;d<5;d=d+1){
			sel.get(d).start();

		}


		for(seller threads : sel){
			
			try{
				threads.join();
			}
			catch(InterruptedException ex){
				System.out.println(ex);
			}

		}


	}
}