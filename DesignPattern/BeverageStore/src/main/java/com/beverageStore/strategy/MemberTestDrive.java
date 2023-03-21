package main.java.com.beverageStore.strategy;

import java.math.BigDecimal;

public class MemberTestDrive {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		SilverMember sm = new SilverMember();
		GoldMember gm = new GoldMember();
		PlatinumMember pm = new PlatinumMember();
		
		System.out.println("---"+sm.getRank()+"---");
		sm.ifHasGift();
		System.out.println("Dear Member, the cost after discoun is: "+sm.whichDiscount(new BigDecimal(100.0)));
		
		System.out.println("---"+gm.getRank()+"---");
		gm.ifHasGift();
		System.out.println("Dear Member, the cost after discoun is: "+gm.whichDiscount(new BigDecimal(100.0)));
		
		System.out.println("---"+pm.getRank()+"---");
		pm.ifHasGift();
		System.out.println("Dear Member, the cost after discoun is: "+pm.whichDiscount(new BigDecimal(100.0)));
		
	}

}
