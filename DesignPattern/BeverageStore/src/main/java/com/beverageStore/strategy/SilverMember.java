package main.java.com.beverageStore.strategy;

public class SilverMember extends Member {

	public SilverMember() {
		gift = new HasNoGift();
		discount = new SilverMemberDiscount();
		setRank("SilverMember");
	}
}
