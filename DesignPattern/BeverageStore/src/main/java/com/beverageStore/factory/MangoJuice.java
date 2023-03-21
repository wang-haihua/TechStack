package main.java.com.beverageStore.factory;

public class MangoJuice extends Beverage {

	public MangoJuice() {
		// TODO Auto-generated constructor stub
		this.name = "Mango Juice";
		this.description = "Mango Juice";
		this.price = 12.0;
	}
	
	@Override
	public Double cost() {
		// TODO Auto-generated method stub
		return this.getPrice();
	}

}
