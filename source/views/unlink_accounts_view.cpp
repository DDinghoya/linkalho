#include "views/unlink_accounts_view.hpp"
#include "views/confirm_view.hpp"
#include "views/worker_view.hpp"
#include "core/file_operations.hpp"

using namespace std;
using namespace brls::i18n::literals;

UnlinkAccountsView::UnlinkAccountsView(bool canUseLed) : ListItem("translations/unlink_accounts_view/title"_i18n)
{
    this->getClickEvent()->subscribe([canUseLed](brls::View* view) {

        brls::StagedAppletFrame* stagedFrame = new brls::StagedAppletFrame();
        stagedFrame->setTitle("translations/unlink_accounts_view/title"_i18n);

        stagedFrame->addStage(
            new ConfirmView(stagedFrame, "translations/unlink_accounts_view/warning"_i18n, false, canUseLed)
        );
        stagedFrame->addStage(
            new WorkerView(stagedFrame, "translations/unlink_accounts_view/working"_i18n, [](){
                unlinkAccount();
            })
        );
        stagedFrame->addStage(
            new ConfirmView(stagedFrame, "translations/unlink_accounts_view/complete"_i18n, true, canUseLed)
        );

        brls::Application::pushView(stagedFrame);
        stagedFrame->registerAction("", brls::Key::PLUS, []{return true;}, true);
        stagedFrame->updateActionHint(brls::Key::PLUS, ""); // make the change visible
        stagedFrame->registerAction("", brls::Key::B, []{return true;}, true);
        stagedFrame->updateActionHint(brls::Key::B, ""); // make the change visible
    });
}