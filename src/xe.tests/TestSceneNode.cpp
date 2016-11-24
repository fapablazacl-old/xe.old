
#include <UnitTest++/UnitTest++.h>

#include <xe/sg/SceneNode.hpp>
#include <xe/sg/Renderable.hpp>

TEST(TestSceneNode)
{
    // setters and getters
    class CustomRenderable : public xe::sg::Renderable {
    public:
        virtual ~CustomRenderable() {}
        virtual void renderWith(xe::sg::Pipeline *renderer) override {}
    };

    auto node = std::make_unique<xe::sg::SceneNode>();
    auto renderable = std::make_unique<CustomRenderable>();

    CHECK(node->setName("node") == node.get());
    CHECK(node->setMatrix(xe::Matrix4f::makeIdentity()) == node.get());
    CHECK(node->setRenderable(renderable.get()) == node.get());

    CHECK_EQUAL(node->getName(), "node");
    CHECK_EQUAL(node->getMatrix(), xe::Matrix4f::makeIdentity());
    CHECK(node->getRenderable() == renderable.get());

    CHECK(node->setName("") == node.get());
    CHECK_EQUAL(node->setMatrix(xe::Matrix4f::makeZero()), node.get());
    CHECK(node->setRenderable(nullptr) == node.get());

    CHECK_EQUAL(node->getName(), "");
    CHECK_EQUAL(node->getMatrix(), xe::Matrix4f::makeZero());
    CHECK(node->getRenderable() == nullptr);

    // hierarchy
    auto child1 = node->createNode()->setName("child1");
    auto child2 = node->createNode()->setName("child2")->setRenderable(renderable.get());
    auto child3 = node->createNode()->setName("child3")->setMatrix(xe::Matrix4f::makeRotateY(3.1415926535));

    CHECK_EQUAL(node->getNodeCount(), 3);
}
