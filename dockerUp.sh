rm target/dap-patternsearch-analysis-service.jar
mvn clean package -DskipTests

sudo docker container rm dap-patternsearch-analysis-service
# sudo docker container rm dap-patternsearch-analysis-service db
# sudo docker container rm dap-patternsearch-analysis-service
sudo docker image rm dap-patternsearch-analysis-service

#mvn clean package -DskipTests
# cp target/dap-patternsearch-analysis-service.jar src/main/docker/

# cd src/main/docker/

# sudo docker compose up

sudo docker build --tag dap-patternsearch-analysis-service .

sudo docker run --publish 9191:9191 --name dap-patternsearch-analysis-service dap-patternsearch-analysis-service