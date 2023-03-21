package main.java.com.beverageStore.decorater;

import java.math.BigDecimal;

import main.java.com.beverageStore.factory.Beverage;

public class Oversize extends Weight {

	public Oversize(Beverage beverage) {
		// TODO Auto-generated constructor stub
		super(beverage);
		this.setPrice(5.0);
		this.setDescription("Oversize");
	}


}
