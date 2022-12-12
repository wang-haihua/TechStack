package main.java.com.beverageStore.factory;

public class HongKongMilkTea extends Beverage {

	public HongKongMilkTea() {
		// TODO Auto-generated constructor stub
		this.name = "HongKongMilkTea";
		this.description = "HongKongMilkTea";
		this.price = 12.0;
	}
	
	@Override
	public Double cost() {
		// TODO Auto-generated method stub
		return this.getPrice();
	}

}
