let $i := doc("bookstore.xml")/bookstore/*/price/text()
return sum($i)
