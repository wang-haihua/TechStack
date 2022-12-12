package main.java.com.beverageStore.decorater;

import main.java.com.beverageStore.factory.Beverage;

public class Pearl extends Material {

	public Pearl(Beverage beverage) {
		// TODO Auto-generated constructor stub
		super(beverage);
		this.setPrice(2.0);
		this.setDescription("Pearl");
	}
}
