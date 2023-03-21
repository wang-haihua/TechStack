package main.java.com.beverageStore.factory;

public class WatermelonJuice extends Beverage {

	public WatermelonJuice() {
		// TODO Auto-generated constructor stub
		this.name = "Watermelon Juice";
		this.description = "Watermelon Juice";
		this.price = 9.0;
	}
	
	@Override
	public Double cost() {
		// TODO Auto-generated method stub
		return this.getPrice();
	}

}
