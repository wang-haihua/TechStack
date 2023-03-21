package main.java.com.beverageStore.decorater;

import main.java.com.beverageStore.factory.Beverage;

public abstract class Material extends Beverage {

	Beverage beverage;
	
	Material(Beverage decoratedBeverage){
		this.beverage = decoratedBeverage;
	}
	
	public String getDescription() {
		return beverage.getDescription() + " " + super.getDescription();
	}
	
	@Override
	public Double cost() {
		// TODO Auto-generated method stub
		return super.getPrice()+beverage.cost();
	}

}
