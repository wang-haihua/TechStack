package main.java.com.beverageStore.strategy;

public class HasNoGift implements Gift {

	@Override
	public void giveaway() {
		// TODO Auto-generated method stub
		System.out.println("Sorry, Your membership level is not enough to have a gift!\n");
	}

}
