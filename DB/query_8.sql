WITH film_rental_count AS 
(
SELECT inventory.film_id AS film_id, COUNT(rental_id) AS film_count 
FROM rental, inventory 
WHERE rental.inventory_id = inventory.inventory_id 
GROUP BY inventory.film_id
) 
SELECT film.*, film_rental_count.film_count AS rental_count 
FROM film_rental_count, film 
WHERE 
film_rental_count.film_count = (SELECT MAX(film_count) FROM film_rental_count) 
AND film_rental_count.film_id = film.film_id;
