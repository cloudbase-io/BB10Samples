/* Copyright (C) 2012 cloudbase.io

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License, version 2, as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.
*/
#include <string>
#include <vector>
#include "CBSerializable.h"

namespace Cloudbase {

#ifndef CBPAYPAL_H
#define CBPAYPAL_H


/***
 * this object represents a single item within a CBPayPalBill object.
 */
class CBPayPalBillItem : public CBSerializable {
public:
	std::string name; /// The name of the item for the transaction
	std::string description; /// An extended description of the item. This should also contain the amount as PayPal does not always display it.
	double amount; /// The amount of the transaction
	double tax; /// additional taxes to be added to the amount
	int quantity; /// a quantity representing the number of items involved in the transaction. for example 100 poker chips

	CBPayPalBillItem();

	std::string serialize();
};

/**
 * This is the bill object for the PayPal digital goods payments APIs. A bill object must contain
 * at least one BillItem.
 *
 * The description of the bill should also contain the total amount as PayPal does not always display
 * the amount in the checkout page.
 */
class CBPayPalBill : public CBSerializable {
public:
	std::string name; /// a name for the purchase
	std::string description; /// a description of the bill item. this should also contain the price for the bill as PayPal will not always display the amount field.
	std::string invoiceNumber; /// this is a user generated unique identifier for the transaction.
	std::vector<CBPayPalBillItem> items; /// this is a list of BillItems. Each CBPayPalBill must have at least one BillItem
	std::string currency; /// The 3 letter ISO code for the transaction currency. If not specified this will automatically be USD
	std::string paymentCompletedFunction; /// This is the code of a CloudFunction to be executed once the payment is completed
	std::string paymentCancelledFunction; /// This is the name of a CloudFunction to be executed if the payment is cancelled
	/**
	 * By default the express checkout process will return to the cloudbase APIs. if you want to override
	 * this behaviour and return to a page you own once the payment is completed set this property to the url
	 */
	std::string paymentCompletedUrl;
	/**
	 * By default the express checkout process will return to the cloudbase APIs. if you want to override
	 * this behaviour and return to a page you own once the payment has been cancelled set this property to the url
	 */
	std::string paymentCancelledUrl;

	CBPayPalBill();

	void addItem(CBPayPalBillItem newItem);

	std::string serialize();
};

#endif

}
