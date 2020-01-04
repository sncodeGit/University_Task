SELECT film_id, COUNT(inventory_id) AS film_count
FROM inventory
WHERE store_id = 1 
GROUP BY film_id
UNION
SELECT film_id, 0 AS film_count
FROM inventory
WHERE film_id NOT IN (SELECT film_id FROM inventory WHERE store_id = 1)
ORDER BY film_id;
