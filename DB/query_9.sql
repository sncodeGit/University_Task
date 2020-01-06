WITH film_rental_count AS 
(
SELECT inventory.film_id AS film_id, COUNT(rental_id) AS film_count 
FROM rental, inventory 
WHERE rental.inventory_id = inventory.inventory_id 
GROUP BY inventory.film_id
) 
,category_rental_count AS 
(
SELECT film_category.category_id, SUM(film_rental_count.film_count) AS category_count 
FROM film_rental_count, film, film_category 
WHERE film_rental_count.film_id = film.film_id 
AND film.film_id = film_category.film_id 
GROUP BY category_id
) 
SELECT name, category_count 
FROM category_rental_count, category
WHERE 
category_count = (SELECT MAX(category_count) FROM category_rental_count) 
AND category_rental_count.category_id = category.category_id;
