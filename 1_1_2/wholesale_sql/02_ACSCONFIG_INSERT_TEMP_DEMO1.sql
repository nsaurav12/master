DELETE FROM TEMP_DEMO1
      WHERE ID IN (1);

COMMIT;


INSERT INTO TEMP_DEMO1 (id, city, country)
    VALUES (1, 'Bangalore', 'India');



COMMIT;