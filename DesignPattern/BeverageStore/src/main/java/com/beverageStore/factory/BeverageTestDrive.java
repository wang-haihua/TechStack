package main.java.com.beverageStore.factory;

import main.java.com.beverageStore.decorater.Oversize;
import main.java.com.beverageStore.decorater.Pearl;

public class BeverageTestDrive {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		BeverageStore fruitJuice = new FruitJuice();
		BeverageStore coffee = new Coffee();
		BeverageStore milkTea = new MilkTea();
		
		Beverage mangoJuice = fruitJuice.orderBeverage("MangoJuice");
		System.out.println("Customer served a " + mangoJuice.getName() +'\n');
		
		Beverage mocha = coffee.orderBeverage("Mocha");
		System.out.println("Customer served a " + mocha.getName() +'\n');
		
		Beverage hongKongMilkTea = milkTea.orderBeverage("HongKongMilkTea");
		System.out.println("Customer served a " + hongKongMilkTea.getName() +'\n');
		Oversize hongKongMilkTea_Oversize = new Oversize(hongKongMilkTea);
		Pearl hongKongMilkTea_Oversize_Pearl = new Pearl(hongKongMilkTea_Oversize);
		System.out.println(hongKongMilkTea_Oversize_Pearl.getDescription()+' '+hongKongMilkTea_Oversize_Pearl.cost());

	}

}
