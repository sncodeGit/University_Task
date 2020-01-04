SELECT name, COUNT(film_id) AS film_count 
FROM category, film_category 
WHERE category.category_id = film_category.category_id 
GROUP BY category.category_id;
