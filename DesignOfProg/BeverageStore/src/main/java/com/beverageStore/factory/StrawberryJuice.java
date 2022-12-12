package main.java.com.beverageStore.factory;

public class StrawberryJuice extends Beverage {

	public StrawberryJuice() {
		// TODO Auto-generated constructor stub
		this.name = "Strawberry Juice";
		this.description = "Strawberry Juice";
		this.price = 10.0;
	}
	@Override
	public Double cost() {
		// TODO Auto-generated method stub
		return this.getPrice();
	}

}
