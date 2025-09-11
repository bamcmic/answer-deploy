#!/bin/bash
set -e

echo "🚀 开始部署 Answer..."

# 更新系统
apt update && apt upgrade -y

# 安装依赖
apt install -y curl git

# 安装 Docker
curl -fsSL https://get.docker.com | sh
systemctl enable docker
systemctl start docker

# 安装 Docker Compose
curl -L "https://github.com/docker/compose/releases/latest/download/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
chmod +x /usr/local/bin/docker-compose

# 创建目录
mkdir -p /opt/answer/data/postgres /opt/answer/data/redis
cd /opt/answer

# 写 docker-compose.yml
cat > docker-compose.yml <<'EOF'
version: '3'

services:
  answer:
    image: registry.cn-hangzhou.aliyuncs.com/answerdev/answer:latest
    ports:
      - "80:80"
    environment:
      DB_TYPE: postgres
      DB_HOST: db
      DB_PORT: 5432
      DB_USER: answer
      DB_PASS: answerpass
      DB_NAME: answer
      REDIS_HOST: redis
      REDIS_PORT: 6379
    depends_on:
      - db
      - redis

  db:
    image: postgres:15
    environment:
      POSTGRES_USER: answer
      POSTGRES_PASSWORD: answerpass
      POSTGRES_DB: answer
    volumes:
      - ./data/postgres:/var/lib/postgresql/data

  redis:
    image: redis:7
    volumes:
      - ./data/redis:/data
EOF

# 启动容器
docker-compose up -d

echo "✅ Answer 部署完成！请访问 http://<爪云公网地址> 进行初始化。"
