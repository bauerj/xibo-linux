#pragma once

#include "AbstractBuilder.hpp"

#include "control/IRegion.hpp"
#include "parsers/RegionOptions.hpp"
#include "adaptors/GtkFixedLayoutAdaptor.hpp"

#include <vector>
#include <boost/optional/optional_fwd.hpp>

class IRegionContent;
class ITimerProvider;
class RegionBuilder;

struct ContentWithPos
{
    std::unique_ptr<IRegionContent> content;
    int x;
    int y;
};

template<>
struct BuilderTraits<RegionBuilder>
{
    using Component = IRegion;
    using DefaultHandler = GtkFixedLayoutAdaptor;
    using Options = ResourcesXlf::RegionOptions;
};

const int DEFAULT_ZORDER = 0;
const bool DEFAULT_LOOP = false;

class RegionBuilder : public AbstractBuilder<RegionBuilder>
{
public:
    RegionBuilder& content(std::vector<ContentWithPos>&& content);

protected:
    RegionBuilder& retrieveOptions(const ResourcesXlf::RegionOptions& opts) override;
    std::unique_ptr<IRegion> create() override;
    void doSetup(IRegion& region) override;

private:
    int getIdOption(int id);
    int getWidthOption(int width);
    int getHeightOption(int height);
    int getZorderOption(const boost::optional<int>& zorderOpt);
    bool getLoopOption(const boost::optional<bool>& loopOpt);

    void loopContent(IRegion& region);
    void addAllContent(IRegion& region);
    void checkWidth(int width);
    void checkHeight(int height);

private:
    int m_id;
    int m_width;
    int m_height;
    int m_zorder;
    bool m_loop;
    std::vector<ContentWithPos> m_content;

};
