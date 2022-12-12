package main.java.com.beverageStore.factory;

public class Coffee extends BeverageStore {

	@Override
	Beverage createBeverage(String item) {
		// TODO Auto-generated method stub
		if(item.equals("Cappuccino")) {
			return new Cappuccino();
		}
		else if(item.equals("Mocha")) {
			return new Mocha();
		}
		else if(item.equals("VanillaLatte")) {
			return new VanillaLatte();
		}
		else {
			return null;
		}
	}

}
