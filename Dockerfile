FROM ubuntu:20.04

COPY ../bigpiseal3.5.1 opt/bigpiseal3.5.1

#datalake for testing
COPY ../datalake opt/datalake

COPY bigpiseal3.5.1/bin/patternSearch/v2/keys keys


RUN mkdir -p opt/bigpiseal3.5.1/bin/patternSearch/v2/data && mkdir -p opt/bigpiseal3.5.1/bin/patternSearch/v2/result && mkdir -p opt/bigpiseal3.5.1/bin/patternSearch/v2/upload && mkdir -p opt/bigpiseal3.5.1/bin/patternSearch/v2/keys

RUN useradd -m bigpi

RUN chown -R bigpi:bigpi /opt/bigpiseal3.5.1/* /opt/datalake/* /opt/bigpiseal3.5.1/bin/patternSearch/v2/data /opt/bigpiseal3.5.1/bin/patternSearch/v2/result /opt/bigpiseal3.5.1/bin/patternSearch/v2/upload /opt/bigpiseal3.5.1/bin/patternSearch/v2/keys
RUN chmod 777 /opt/bigpiseal3.5.1 /opt/datalake /opt/bigpiseal3.5.1/bin/patternSearch/v2/data /opt/bigpiseal3.5.1/bin/patternSearch/v2/result /opt/bigpiseal3.5.1/bin/patternSearch/v2/upload /opt/bigpiseal3.5.1/bin/patternSearch/v2/keys



RUN apt-get update && apt-get install wget unzip zip -y
#RUN apt-get install wget unzip zip -y
    
# ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install --no-install-recommends -y \
    g++ \
    make \
    cmake \
    libc6-dev \
    libboost-program-options-dev
#    git \
#    ca-certificates

#RUN mkdir -p storage && mkdir -p storage/data && mkdir -p storage/result && mkdir -p storage/upload
#RUN mkdir -p keys && mkdir -p storage && mkdir -p storage/data && mkdir -p storage/result && mkdir -p storage/upload

RUN cd opt/bigpiseal3.5.1 && cmake . && make && make install && cmake . -DSEAL_BUILD_EXAMPLES=ON && make
#RUN cd opt/bigpiseal3.5.1 && cmake . && make && make install && cmake . -DSEAL_BUILD_EXAMPLES=OFF && make


RUN apt-get -y update && apt-get install -y openjdk-8-jdk && apt-get clean
#RUN apt install openjdk-8-jdk
#RUN apt-get -y update
#RUN mkdir -p /usr/share/man/man1/
#RUN apt-get install -y openjdk-8-jdk
#RUN apt-get install -y openjdk-8-jre
#RUN update-alternatives --config java
#RUN update-alternatives --config javac

#WORKDIR /usr/src
WORKDIR /opt/datalake

USER bigpi

ADD target/dap-patternsearch-analysis-service.jar dap-patternsearch-analysis-service.jar
ENTRYPOINT ["java", "-jar", "dap-patternsearch-analysis-service.jar"]
EXPOSE 9191